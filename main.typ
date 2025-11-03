#import "@preview/cmarker:0.1.6"

#outline()

#cmarker.render(
  read("README_processed_linked.md"), 
  h1-level: 2,
  scope: (image: (path, alt: none) => image(path, alt: alt))
  )