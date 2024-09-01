Get-ChildItem -Hidden -Recurse -Exclude .git | Remove-Item -Force -Recurse -Verbose
Remove-Item -Path x64, 'visual data structures/x64' -Recurse -Verbose

git checkout master
git add .

Write-Output "
please type a commit message
"

$message = Read-Host
git commit -m $message 

git push -u origin master