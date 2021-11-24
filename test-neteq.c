#include <stdio.h>
#include "audio-neteq.h"

int main() 
{
    const int kSampleRateHz = 48000;
    const int kPlayloadType = 96;
    FILE* pcm = fopen("48.pcm", "rb");
    if (pcm == NULL) {
        printf("open pcm file failed!\n");
        return -1;
    }
    FILE* outfile = fopen("plc.pcm", "wb");
    while (1) {


        if (init_neteq(kSampleRateHz, 1, kPlayloadType) == -1) {
            printf("init neteq failed!\n");
            return -1;
        }

        int timestamp = 0;
        short seq_no = 0;
        const int kFframSizeMs = 10;
        const int kSamples = 480;

        short inputSample[480] = { 0 };
        short outputSample[480] = { 0 };
        while (!feof(pcm)) {
            int read = fread(inputSample, sizeof(short), kSamples, pcm);
            if (read != kSamples) {
                printf("read: %d\n", read);
                break;
            }
            //if (seq_no % 4 != 1) { // test expand and merge
                if (insert_packet(seq_no, timestamp, inputSample, kSamples) == -1) {
                    printf("neteq insert audio failed!\n");
                    return -1;
                }
           // }
            ++seq_no;
            timestamp += kSamples;

            //if (seq_no % 5 == 0) { // test accelerate
            if (!get_audio(outputSample)) {
                printf("neteq get audio failed!\n");
                return -1;
            }

            fwrite(outputSample, sizeof(short), kSamples, outfile);
            //}

        }
        //while (get_audio(outputSample)) {
        //    fwrite(outputSample, sizeof(short), kSamples, outfile);
        //    
        //}
        
        fseek(pcm, 0, SEEK_SET);
        clear_neteq();
    }
    fflush(outfile);
    fclose(outfile);
    fclose(pcm);
    return 0;
}