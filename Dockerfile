FROM mcr.microsoft.com/devcontainers/jekyll:bullseye

ARG NODE_VERSION="none"

RUN if [ "${NODE_VERSION}" != "none" ]; then \
        su vscode -c "umask 0002 && . /usr/local/share/nvm/nvm.sh && nvm install ${NODE_VERSION}"; \
    fi

WORKDIR /srv/jekyll/kawapa.github.io

CMD ["/bin/bash", "-c", "./post-create.sh && bundle exec jekyll serve"]

# docker run -d --network=host -v /home/${USER}/Private/gh:/srv/jekyll kawapa.github.io:latest