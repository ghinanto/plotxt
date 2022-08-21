FROM archlinux:base

COPY library-scripts/packages-arch packages

RUN pacman -Syu --noconfirm $(cat packages) \
  && rm -f /packages