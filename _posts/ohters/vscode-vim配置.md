---
layout:     post
title:      vscode-vim配置 
subtitle:   vscode-vim 
date:       2024-01-11 09:44:26
author:     Pan Wang (panwang725@gmail.com)
header-img: img/green-bg.jpg
catalog: true
tags:
    - vscode
    - vim  
---

## vscode-vim配置意义

    + 本身vim写代码效率就比较高，可以让我们摆脱鼠标的束缚，让我们可以专注于代码本身；但是在 terminal 用vim总是感觉过于麻烦。

    + vscode本身就是一个轻量化的 IDE, 有的插件用起来还是很方便的。

    + 综合考虑，不如我们配置一个 vscode-vim结合起来的编程环境，既能保证平常写代码时的专注，又不失插件带来的便利性。

## vscode-vim配置过程

    + step1: 在vscode中安装vim插件。

    + step2: 配置vim configure，也就是vim本身的一些快捷键，主要是在settings.json这个文件里面，采用json格式，vim开头的就是相关配置。

    + step3: 配置vscode configure，本身vscode也有很多的快捷键，也是需要我们去设置的，在 keybindings.json这个文件里面。

## settings.json

|   Command    |         Description           |
|--------------|-------------------------------|
| `<leader>` l | Last Character In The Line    |
| `<leader>` h | First Character In The Line   |
| K            | Move 5 Line Up                |
| J            | Move 5 Line Down              |
| jj           | Exit Insert Mode              |
| CTRL j       | View Focus Above Editor Group |
| CTRL k       | View Focus Below Editor Group |
| CTRL h       | View Focus Left Editor Group  |
| CTRL l       | View Focus Right Editor Group |

## keybindings.json

|    Command     |         Description           |
|----------------|-------------------------------|
| `<leader>` w   | File Save                     |
| `<leader>` s   | Toggle Side Bar Visibility    |
| `<leader>` e   | Toggle File Exploer           |
| `<leader>` g   | Toggle Git Exploer           |
| `<leader>` ds  | Duplicate Selection           |
| `<leader>` q   | View Close Editor             |
| `<leader>` o   | Go To File In Editor          |
| `<leader>` p   | Show All Commands             |
| `<leader>` nh  | Notifications Hide            |
| `<leader>` nc  | Notifications Clear All       |
| `<leader>` nf  | Notifications Focus All       |
| `<leader>` ns  | Notifications Show            |
| `<leader>` gl  | Go To Line / Column           |
| `<leader>` fb  | Focus Breadcrumbs             |
| `<leader>` vih | Increase Editor Height        |
| `<leader>` vdh | Decrease Editor Height        |
| `<leader>` viw | Increase Editor Width         |
| `<leader>` vdw | Decrease Editor Width         |
| `<leader>` me  | Maximize Editor Group         |
| `<leader>` vn  | View Open Next Editor                |
| `<leader>` vp  | View Open Previous Editor            |
| `<leader>` ceg | View Close Editor Group              |
| `<leader>` coe | View Close Other Editors In Group    |
| `<leader>` sh  | View Split Editor Left               |
| `<leader>` sj  | View Split Editor Down               |
| `<leader>` sk  | View Split Editor Up                 |
| `<leader>` sl  | View Split Editor Right              |
| a       | File New File                |
| A       | File New Folder              |
| y       | File Copy                    |
| x       | File Cut                     |
| p       | File Paste                   |
| r       | File Rename                  |
| d       | File Move To Trash           |
| D       | File Delete Permanent        |
| c       | File Collapse Folders        |
| t       | Open In Integrated Terminal  |
| u       | Copy Path                    |
| i       | Copy Relative Path           |
| CTRL m  | View Toggle Maximized Panel      |
| CTRL ~  | Activate or Close Terminal       |
| CTRL J  | Terminal Scroll Down (Line)      |
| CTRL H  | Terminal Scroll Down (Page)      |
| CTRL K  | Terminal Scroll Down (Line)      |
| CTRL L  | Terminal Scroll Down (Page)      |
| CTRL n  | Terminal Focus Next Terminal     |