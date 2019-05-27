#include <vlc/vlc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv)
{
    const char* source = "rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mov";
    libvlc_instance_t* vlc = libvlc_new(0, NULL);
    libvlc_media_player_t* media_player = libvlc_media_player_new(vlc);
    libvlc_media_t* media = libvlc_media_new_location(vlc, source);
    libvlc_media_add_option(media, ":sout=#rtp{sdp=rtsp://127.0.0.1:5554/1}");
    libvlc_media_player_set_media(media_player, media);
    libvlc_media_release(media);
    libvlc_media_player_play(media_player);

    libvlc_instance_t* vlc2 = libvlc_new(0, NULL);
    libvlc_media_player_t* media_player2 = libvlc_media_player_new(vlc2);
    libvlc_media_t* media2 = libvlc_media_new_location(vlc2, source);
    libvlc_media_add_option(media2, ":sout=#rtp{sdp=rtsp://127.0.0.1:5554/2}");
    libvlc_media_player_set_media(media_player2, media2);
    libvlc_media_release(media2);
    libvlc_media_player_play(media_player2);

    system("PAUSE");

    libvlc_media_player_stop(media_player);
    libvlc_media_player_release(media_player);
    libvlc_release(vlc); // If this line moves after the media_player_release(2), it doesn't crash.
    libvlc_media_player_stop(media_player2);
    libvlc_media_player_release(media_player2);
    libvlc_release(vlc2); 
    return 0;
}