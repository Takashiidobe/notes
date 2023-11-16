SOURCE_DOCS := $(shell find src -type f -name "*.md")

HTML_FILES=$(SOURCE_DOCS:src/%.md=site/%.html)

all: html books fix_links copy_files
	firefox site/index.html

deploy: html fix_links copy_files build_index
	ntl deploy --prod

html: mkdirs $(HTML_FILES)

site/%.html: src/%.md templates/site.html
	pandoc -f markdown+fenced_divs -s $< -o $@ --table-of-contents --mathjax --filter pandoc-sidenote --filter d2-filter --section-divs --template templates/site.html

build_index: $(SOURCE_DOCS)
	pagefind --site site

copy_files: templates/main.js
	cp templates/*{.css,.js} site/

fix_links: $(HTML_FILES)
	./bin/convert-html.sh

clean:
	rm -r site/**/*.html

books:
	./bin/generate_books_md.py

.PHONY: mkdirs
mkdirs:
	rsync -a --include='*/' \
	--include="*.png" \
	--include="*.jpg" \
	--include="*.jpeg" \
	--include="*.gif" \
	--exclude='*' src/ site/
	rsync -a --include='*/' \
	--include="*.png" \
	--include="*.jpg" \
	--include="*.jpeg" \
	--include="*.svg" \
	--include="*.gif" \
	--exclude='*' src/img/ site/img
