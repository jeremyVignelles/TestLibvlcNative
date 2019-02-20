FROM registry.videolan.org:5000/vlc-debian-win64

COPY build-qt.sh /

ENV TARGET_PLATFORM win64
RUN /build-qt.sh && rm /build-qt.sh
COPY Toolchain* /
ENV PATH="/opt/qt/bin:${PATH}"