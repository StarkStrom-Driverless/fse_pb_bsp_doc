#import "@preview/cmarker:0.1.6"

#align(center, [
  #heading(bookmarked: false, [
    #text(size: 20pt, [
      Documentation Repository for 
    ])
  ])

  #heading(bookmarked: false, [
    #text(size: 14pt, [
      fse_pb_bsp
    ])
  ])

  #heading(bookmarked: false, [
    #text(size: 10pt, [
      v_0.0.1
    ])
  ])

  #v(60pt)

  Maximilian Hoffmann \
  #link(
    "maximilian.hoffmann@starkstrom-augsburg.de"
  )
  
])

#pagebreak()

#outline()

#show heading.where(level: 1): it => {
  pagebreak(weak: true)

}

#show heading.where(level: 2): it => {
  pagebreak(weak: true)
  it
}

#show raw.where(block: true): it => {
  block(
    width: 100%,
    fill: luma(250),
    stroke: 1pt + luma(200),
    radius: 4pt,
    inset: 10pt,
    it
  )
}

#cmarker.render(
  read("README_processed_linked.md"), 
  scope: (image: (path, alt: none) => image(path, alt: alt))
)
