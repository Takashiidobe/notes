window.addEventListener('load', (event) => {
  new PagefindUI({ element: "#search" });
  var params = new URLSearchParams(document.location.search);
  var markInstance = new Mark(document.body);
  var t = params.get("h") || '';

  function highlight() {
    let selected = document.getSelection();
    if (selected.anchorNode) {
      t = selected;
      params.set("h", t);
    }

    if (window.history.replaceState) {
      const url = window.location.protocol
        + "//" + window.location.host
        + window.location.pathname
        + "?"
        + params.toString();

      window.history.replaceState({ path: url }, "", url);
      markInstance.unmark({
        done: () => {
          markInstance.mark(t.toString(), {separateWordSearch: false});
        }
      });
    }
  }

  highlight();
  document.addEventListener("mouseup", highlight);
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

function appendCss(link, filepath, serverpath) {
  var protocol = window.location.protocol;
  if (protocol === 'file:') {
    link.href = filepath;
  }
}

var linkStyles = document.querySelector('#styles');
var pagefindStyles = document.querySelector('#pagefind-styles');

appendCss(linkStyles, "/home/takashiidobe/monorepo/notes/site/styles.css", "/styles.css");
appendCss(pagefindStyles, "/home/takashiidobe/monorepo/notes/site/_pagefind/pagefind-ui.css", "/_pagefind/pagefind-ui.css");
