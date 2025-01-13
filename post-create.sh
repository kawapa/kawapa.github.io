sed -i 's/^# gem "/gem "/' Gemfile
sed -i 's/^# theme: just-the-docs/theme: just-the-docs/' _config.yml
sed -i 's/^remote_theme: kawapa\/just-the-docs/# remote_theme: kawapa\/just-the-docs/' _config.yml

if [ -f Gemfile.lock ] && grep "BUNDLED WITH" Gemfile.lock > /dev/null; then
    cat Gemfile.lock | tail -n 2 | grep -C2 "BUNDLED WITH" | tail -n 1 | xargs gem install bundler
fi

if [ -f Gemfile ]; then
    bundle install
fi