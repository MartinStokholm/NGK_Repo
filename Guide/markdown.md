# This is a markdown document.
Open it with any text editor, and its fairly readeble. 
This is its main strength, over other markup languages, like latex. 


## Extention for preview
Open it in visual studio code and finde the extention: markdown all in one. 
This allows you to preview your document among others things. 
![](figs/PreviewButton.png)

headings are made with # 
# h1 
## h2
### h3
and so forth. 

# Code snippet 
Code snippets are made with "```"

Like This

```
 <some code snippet>
```
Want syntax? Write the desired code languages to syntax highlight right after the first "```"
Like so:

```cpp 
int main () {
    int age; 

}
```

# Screen shots 

```
![](<path to picture>)
```
![](screenshot.png)
Or alternatively from an other folders 
![](figs/screenshot.png)

## Comments
To comment something out use syntax '[//]: <>', eg.

[//]: <This text has been commented out>

Or '[comment]: <>'

[comment]: <You can't see this text either>

Comments must be separated from the text you want to display with an empty line.

## Lists

1. Numbered lsitems
   1. tap to indent list
2. enter to make new intry
3. or write manualy. 

- Unnumbered list
- 2 
- 3
## Exporting
There are many ways to puplish markdown documents. 
With the extention markdown all in one, the .md files kan be converted to html document to be readble by browsers. 

If you instead want pdfs, word document, latex or other formats from your markdown document, pandoc is the way to go. 
Pandoc is an exporting and convertion application. 
install it with your packaged maneger like so
``` 
sudo apt install pandoc 
# or 
brew install pandoc
```
From the command line you can then run pandoc cmds.
```
pandoc -s -V geometry:margin=1in -o <output_destination> <input_file1> <input_file2>
```
-s standalone file. Makes sure the files are readeble by them self. f.x. using correct html header and body. 
-o <output_destination> indecates that the output is other then stdout
-V geometry:margin=1in adds a geotry varieble that makes nicly sized margins. 


