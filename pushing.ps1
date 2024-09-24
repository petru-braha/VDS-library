Get-ChildItem -Hidden -Recurse -Exclude .git | Remove-Item -Force -Recurse -Verbose
Remove-Item -Path 'process 0 start/x64', 'process 1 test/x64', 'process 2 draw/x64' -Recurse -Verbose
Remove-Item -Path 'process 0 start/stderr log.txt', 'process 1 test/stderr log.txt', 'process 2 draw/stderr log.txt' -Recurse -Verbose

git checkout master
git add .

Write-Output "
please type a commit message
"

$message = Read-Host
git commit -m $message 

git push -u origin master