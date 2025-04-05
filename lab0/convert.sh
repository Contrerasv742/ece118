#!/bin/bash
# Create the YAML metadata file
cat > metadata.yaml << EOL
---
documentclass: article
classoption: 12pt
geometry: margin=1in
header-includes:
    - \usepackage{graphicx}
    - \usepackage{float}
    - \usepackage{caption}
    - \usepackage{etoolbox}
    - \AtBeginEnvironment{figure}{\centering}
    - \floatplacement{figure}{H}
---
EOL

# Create a Catppuccin-themed syntax highlighting file
cat > catppuccin.theme << EOL
{
    "text-color": "#cdd6f4",
    "background-color": "#1e1e2e",
    "line-number-color": "#6c7086",
    "line-number-background-color": "#1e1e2e",
    "text-styles": {
        "Normal": {
            "text-color": "#cdd6f4"
        },
        "Keyword": {
            "text-color": "#cba6f7",
            "bold": true
        },
        "Function": {
            "text-color": "#89b4fa"
        },
        "Variable": {
            "text-color": "#f5c2e7"
        },
        "ControlFlow": {
            "text-color": "#f38ba8",
            "bold": true
        },
        "Type": {
            "text-color": "#fab387",
            "bold": true
        },
        "String": {
            "text-color": "#a6e3a1"
        },
        "Constant": {
            "text-color": "#fab387"
        },
        "SpecialChar": {
            "text-color": "#f9e2af"
        },
        "Comment": {
            "text-color": "#7f849c",
            "italic": true
        },
        "Operator": {
            "text-color": "#89dceb"
        },
        "Alert": {
            "text-color": "#f38ba8",
            "background-color": "#313244",
            "bold": true
        }
    }
}
EOL

# Correct variable assignment syntax
DOC="docs/prelab0.md"
PDF="docs/prelab0.pdf"

# Run pandoc with options and Catppuccin syntax highlighting
pandoc \
  metadata.yaml \
  "$DOC" \
  -o "$PDF" \
  --pdf-engine=pdflatex \
  -f markdown-smart \
  --toc \
  --number-sections \
  -V colorlinks=true \
  -V linkcolor=blue \
  -V urlcolor=blue \
  -V toccolor=blue \
  --standalone \
  --highlight-style=latte.theme\
  --resource-path=.:./images:./figures:./imgs

# Clean up
rm metadata.yaml
rm catppuccin.theme
