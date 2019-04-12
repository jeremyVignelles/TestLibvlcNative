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
    libvlc_media_player_set_time(media_player, 10000);

    system("PAUSE");

    libvlc_media_player_release(media_player);
    libvlc_release(vlc); 
    return 0;
}