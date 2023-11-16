window.addEventListener('load', (_) => {
  new PagefindUI({ element: "#search" });
});

const targetNode = document.body;
const config = { attributes: false, childList: true, subtree: true };
const callback = (mutationList, observer) => {
  var links = document.querySelectorAll('.pagefind-ui__result-link');
  for (const link of links) {
    link.href = link.href.replace('/file:', 'file:');
  }
};


const observer = new MutationObserver(callback);
observer.observe(targetNode, config);

function appendCss(link, filepath) {
  var protocol = window.location.protocol;
  if (protocol === 'file:') {
    link.href = filepath;
  }
}

var tufteStyles = document.querySelector('#tufte-styles');
var tufteExtraStyles = document.querySelector('#tufte-extra-styles');
var pandocStyles = document.querySelector('#pandoc-styles');
var pandocSolarizedStyles = document.querySelector('#pandoc-solarized-styles');
var pagefindStyles = document.querySelector('#pagefind-styles');

appendCss(tufteStyles, "/home/takashi/monorepo/notes/site/tufte.css", "/tufte.css");
appendCss(tufteExtraStyles, "/home/takashi/monorepo/notes/site/tufte-extra.css", "/tufte-extra.css");
appendCss(pandocStyles, "/home/takashi/monorepo/notes/site/pandoc.css", "/pandoc.css");
appendCss(pandocSolarizedStyles, "/home/takashi/monorepo/notes/site/pandoc-solarized.css", "/pandoc-solarized.css");
appendCss(pagefindStyles, "/home/takashi/monorepo/notes/site/pagefind/pagefind-ui.css", "/pagefind/pagefind-ui.css");

var previousLinks = Array.from(document.querySelectorAll('p > a')).map(a => a.previousSibling.textContent.includes('Prev:') && a.href).filter(a => a);

var nextLinks = Array.from(document.querySelectorAll('p > a')).map(a => a.previousSibling.textContent.includes('Next:') && a.href).filter(a => a);

if (previousLinks.length > 0) {
  document.addEventListener('keydown', (e) => {
    if (e.keyCode == '104' || e.keyCode == '37') {
      window.location = previousLinks[0];
    }
  });
}

if (nextLinks.length > 0) {
  document.addEventListener('keydown', (e) => {
    if (e.keyCode == '108' || e.keyCode == '39') {
      window.location = nextLinks[0];
    }
  });
}

const hidePageNode = document.head.querySelector('#hide-page');
hidePageNode.remove();
