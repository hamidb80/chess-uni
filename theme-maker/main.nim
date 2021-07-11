import json, os
import pixie, chroma

func replaceImageColor(img: Image, newColor: ColorRGBX): Image =
  result = img
  template pxl: untyped = result.data[i]

  for i in 0..<result.data.len:
    pxl = ColorRGBX(
      r: newColor.r,
      g: newColor.g,
      b: newColor.b,
      a: pxl.a)

type
  InputData = object
    input: string
    output: string

    styles: seq[string]

    colors: seq[tuple[
      name, whiteColor, blackColor: string]]

    pictures: tuple[
      pawn, rook, knight, bishop, queen, king: string]


if isMainModule:
  let data = "./input.json".readFile.parseJson.to InputData

  let 
    outputPath = data.output
    inputPath = data.input 

  if dirExists outputPath: removeDir outputPath
  createDir outputPath

  for color in data.colors:
    for style in data.styles:
      let themeDest = outputPath / style / color.name
      createDir themeDest

      for (pname, ppath) in [
        ("pawn", data.pictures.pawn),
        ("rook", data.pictures.rook),
        ("knight", data.pictures.knight),
        ("bishop", data.pictures.bishop),
        ("queen", data.pictures.queen),
        ("king", data.pictures.king)]:
        
        let img = readImage inputPath / style  / ppath
        replaceImageColor(img,
          color.whiteColor[1..^1].parseHex.asRgbx).writeFile(themeDest/(pname & "-white.png"))
        replaceImageColor(img,
          color.blackColor[1..^1].parseHex.asRgbx).writeFile(themeDest/(pname & "-black.png"))
