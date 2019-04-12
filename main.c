#include <vlc/vlc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv)
{
    const char* options[] = { "-vv" };
    libvlc_instance_t* vlc = libvlc_new(1, options);
    libvlc_media_player_t* media_player = libvlc_media_player_new(vlc);

    libvlc_media_t* media = libvlc_media_new_location(vlc, "file:///D:\\Projects\\Tests\\TestLibvlcNative\\bin\\video.zip#!/video.ts");

    libvlc_media_player_set_media(media_player, media);
    libvlc_media_release(media);

    libvlc_media_player_play(media_player);

    system("PAUSE");
    printf("length : %ld \n", libvlc_media_player_get_length(media_player));
    /* // Just add or remove one / here to switch between blocks
    //Fails with
    // [000000000303ab20] main input warning: INPUT_CONTROL_SET_TIME 10000000 failed or not possible
    libvlc_media_player_set_time(media_player, 10000);
    /*/
     // Seeks, but freezes a little and shows
     // [0000000002fe40c0] archive stream_extractor debug: intrinsic seek failed: 'Internal error: No format_seek_data_block function registered' (falling back to dumb seek)
    libvlc_media_player_set_position(media_player, 0);
    //*/
    system("PAUSE");

    libvlc_media_player_release(media_player);
    libvlc_release(vlc); 
    return 0;
}