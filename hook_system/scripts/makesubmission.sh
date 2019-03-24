#!/bin/bash  
AssignmentId=$1
StudentNumber=$2
StudentFirstname=$3
StudentLastname=$4
FilePath=$5
Username=$6
Password=$7
TempFolder="temp"
UploadTar="upload.tar.gz"

Response=$(curl \
 --request POST \
 -H "Content-Type: application/json" \
 -d "{\"email\": \"$Username\", \"password\": \"$Password\"}" \
 -k \
 -i \
 https://localhost:5001/api/auth/login)

echo "$Response"
Token=$(echo "$Response" | tr ',' '\n' | grep auth_token | cut -d':' -f2)
echo "${Token//\"}"

Response=$(curl  \
 --request POST \
 -H "Authorization: Bearer ${Token//\"}" \
 -F "AssignmentId=$AssignmentId" \
 -F "StudentNumber=$StudentNumber" \
 -F "StudentFirstname=$StudentFirstname" \
 -F "StudentLastname=$StudentLastname" \
 -k \
 -i \
 https://localhost:5001/api/submission)
echo "$Response"
SubmissionId=$(echo "$Response" | tr ',' '\n' | grep submissionId | cut -d':' -f2)
echo "$SubmissionId"

rm -rf "temp"
mkdir temp
cp -r "$FilePath" "temp/"
tar -cvzf "$UploadTar" "temp/" 
rm -rf "temp"

curl -X PUT -F "file=@$UploadTar" -k "https://localhost:5001/api/submission/$SubmissionId/tar" -H "Authorization: Bearer ${Token//\"}"

rm "$UploadTar"