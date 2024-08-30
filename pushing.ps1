Get-ChildItem -Hidden -Recurse -Exclude .git | Remove-Item -Force -Recurse -Verbose
Remove-Item -Path x64, 'visual data structures/x64' -Recurse -Verbose

#read parameter : message
git checkout master
git add .
#git commit -m message
#git push -u origin master