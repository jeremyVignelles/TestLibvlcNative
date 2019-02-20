// Inspired by https://github.com/videolan/vlc-3.0/tree/master/doc/libvlc/QtPlayer

#ifndef PLAYER
#define PLAYER

#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <vlc/vlc.h>

class Mwindow : public QMainWindow {

    Q_OBJECT

        public:
               Mwindow();
               virtual ~Mwindow();

        private slots:
               void openFile();
               void play();
               void stop();
               void mute();
               void about();
               void fullscreen();

               int changeVolume(int);
               void changePosition(int);
               void updateInterface();

        protected:
               virtual void closeEvent(QCloseEvent*);

        private:
               QPushButton *playBut;
               QSlider *volumeSlider;
               QSlider *slider;
               QWidget *videoWidget;

               libvlc_instance_t *vlcInstance;
               libvlc_media_player_t *vlcPlayer;

               void initUI();
};


#endif