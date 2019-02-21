#include <QCoreApplication>
#include <QTimer>
#include <QMutex>
#include <QWaitCondition>
#include <vlc/vlc.h>
#include <iostream>

void onVlcLog(void* data, int level, const libvlc_log_t* context, const char* format, va_list args)
{
    char message[1024 * 16];
    memset(message, 0, sizeof(char) * 1024 * 16);

    vsnprintf(message, 1024 * 16, format, args);

    std::cout << message << std::endl;
}

struct snapshot_data_t {
    QMutex* mutex;
    QWaitCondition* screenshotDone;
};

void onLibvlcSnapshotTaken(const struct libvlc_event_t *p_event, void *p_data)
{
    auto data = (snapshot_data_t*)p_data;
    data->mutex->lock();
    data->screenshotDone->wakeAll();
    data->mutex->unlock();
}

void run()
{
    static const char* const args[] = {
        "--vout", "dummy",                  /* we don't want video (output)   */
        "--no-audio",                       /* we don't want audio (decoding) */
        "-vv"
    };
    auto vlcInstance = libvlc_new(sizeof(args) / sizeof(*args), args);
    //libvlc_log_set(vlcInstance, onVlcLog, NULL);

    //* // Just remove a leading / here to switch between media
    QString inputUrl ="file:///D:\\VideoSamples\\01_llama_drama_270p.mp4";
    /*/
    QString inputUrl ="file:///D:\\VideoSamples\\small.ogv";
    //*/
    auto vlcMedia = libvlc_media_new_location(vlcInstance, inputUrl.toStdString().c_str() );
    auto vlcPlayer = libvlc_media_player_new_from_media (vlcMedia);
    libvlc_media_release(vlcMedia);
    libvlc_media_player_play(vlcPlayer);

    auto event = libvlc_media_player_event_manager(vlcPlayer);

    QMutex mutex;
    QWaitCondition screenshotDone;

    snapshot_data_t snapshotData {
        &mutex,
        &screenshotDone
    };

    libvlc_event_attach(event, libvlc_MediaPlayerSnapshotTaken, onLibvlcSnapshotTaken, &snapshotData);

    libvlc_video_take_snapshot(vlcPlayer, 0, "snapshot.png", 200,200);
    mutex.lock();
    auto isDone = screenshotDone.wait(&mutex, 5000);
    mutex.unlock();

    libvlc_media_player_stop(vlcPlayer);
    std::cout << "player stopped" << std::endl;
    libvlc_media_player_release(vlcPlayer);
    std::cout << "player released" << std::endl;
    libvlc_release(vlcInstance);
    std::cout << "vlc released" << std::endl;

    QCoreApplication::exit(0);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTimer::singleShot(0, run);
    return a.exec();
}
