FROM debian:testing
RUN apt-get update -yq && \
    apt-get install \
        --yes \
        --no-install-recommends \
        ca-certificates \
        g++ \
        make \
        meson \
        && \
    apt-get autoclean && \
    apt-get autoremove && \
    apt-get clean && \
    rm -rf /tmp/* /var/tmp/* && \
    rm -rf /var/lib/apt/lists
