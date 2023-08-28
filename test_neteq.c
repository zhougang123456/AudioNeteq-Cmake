#include <stdio.h>
#include "audio-neteq.h"

int main() 
{
    const int kSampleRateHz = 48000;
    const int kPlayloadType = 97;
    FILE* pcm = fopen("test.pcm", "rb");
    if (pcm == NULL) {
        printf("open pcm file failed!\n");
        return -1;
    }
    FILE* outfile = fopen("plc.pcm", "wb");
    while (1) {

        NeteqContext* context = init_neteq(kSampleRateHz, 2, kPlayloadType);
        if (context == NULL) {
            printf("init neteq failed!\n");
            return -1;
        }

        int timestamp = 0;
        short seq_no = 0;
        const int kFframSizeMs = 10;
        const int kSamples = 480;

        short inputSample[960] = { 0 };
        short outputSample[960] = { 0 };
        while (!feof(pcm)) {
            int read = fread(inputSample, sizeof(short) * 2, kSamples, pcm);
            if (read != kSamples) {
                printf("read: %d\n", read);
                break;
            }
            //if (seq_no % 4 != 1) { // test expand and merge
                if (neteq_insert_packet(context, seq_no, timestamp, inputSample, kSamples) == -1) {
                    printf("neteq insert audio failed!\n");
                    return -1;
                }
           // }
            ++seq_no;
            timestamp += kSamples;

            //if (seq_no % 2 == 0) { // test accelerate
            if (!neteq_get_audio(context, outputSample)) {
                printf("neteq get audio failed!\n");
                return -1;
            }
            printf(" opration %d \n", neteq_get_last_operator(context));
            fwrite(outputSample, sizeof(short) * 2, kSamples, outfile);
            //}

        }
        while (neteq_get_audio(context, outputSample)) {
            printf(" opration %d \n", neteq_get_last_operator(context));
            fwrite(outputSample, sizeof(short) * 2, kSamples, outfile);
            
        }
        
        fseek(pcm, 0, SEEK_SET);
        clear_neteq(context);
    }
    fflush(outfile);
    fclose(outfile);
    fclose(pcm);
    return 0;
}