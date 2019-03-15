# Notes on a Test Harness

These files were collected from previous coding exercises, assignments and google code jam.

This test suite is intended for use with The Hook System developed as the software engineering project associated with [Brock University's 4F00 course](http://www.cosc.brocku.ca/~bockusd/4f00/4f00.html) run in 2018/2019.

The test suite can be used to test functionality of the whole system and should demonstrate the following:

### UI:

- Instructor course file hierarchy is displayed in an intuitive way following `Year/Term/Course-type/Course-number/Evaluations`

- Files containing submissions can be easily selected for processing

- Whitelisted code can be easily viewed and added to

### Protecting Student Data

- Student data is scrubbed from all files when submissions are selected for processing by the instructor

	- For each student name/number, a hash is created and stored in a local database

	- Any instance of the student name/number in a particular file is replaced with the hash

	- Any files that are not scrubbed are reported back to the UI before packaging can be completed

	- hyphens, name changes, non-English characters are handled in a predicatable and reasonable way

- Student data is packaged and sent to the processing server

	- Upon selection, files are bundled, scrubbed of identifying data and packaged into a tar

	- tar is sent to the processing server where plagiarism detection occurs

	- results are sent back to client as an xml string

	- hashes used to obscure student data are identified in the xml string and matched with the database

	- instructor can view results as associated with student name/number

- This can be tested by running any student file through the scrubbing script and checking the result.


### Detecting Plagiarism

- 


## Notable notables

Notable names and numbers:

- student names were inspired by real names of notable contributors to
  the field of computer science

- names with hyphens, non-english characters and middle names were used to
  thoroughly test the limits of the system

- some names and student numbers differ slightly between what is listed on the file header and the student comments to account for common student behaviour 

Notable files:

- Java 
  - 1P02 ([A1](Year/2018-2019/Fall/COSC/1P02/A1/)) xmastree and christmasTree should be identified as completely plagiarized, with
changed variables and class names ([2018-2019](Year/2018-2019/Fall/COSC/1P02/A1/) Richard and Ada, [2015-2016](Year/2015-2016/Fall/COSC/1P02/A1/), [2016-2017](Year/2016-2017/Fall/COSC/1P02/A1/), [2017-2018](Year/2017-2018/Fall/COSC/1P02/A1/) Noam ) other files are originals.
  
  - 1P02 ([A2](Year/2018-2019/Fall/COSC/1P02/A2/)) should be different between this year's students but should be matched with students from [2015-2016](Year/2015-2016/Fall/COSC/1P02/A2/)

  - 1P02 ([A3](Year/2018-2019/Fall/COSC/1P02/A3/)) should have a matching section between Richard and al, should be plagiarized between Alan and Noam [2015-2016](Year/2015-2016/Fall/COSC/1P02/A3/), one of the files from Ada is plagiarized from Grace [2015-2016](Year/2015-2016/Fall/COSC/1P02/A3/)

  - 1P02 ([A4](Year/2018-2019/Fall/COSC/1P02/A4/)) all students should use whitelisted drawTriangle() method but are otherwise unique

- C++

  - 2P03 ([A1](Year/2018-2019/Fall/COSC/2P03/A1)) MatrixBuilder and GridBuilder should be identified as completely plagiarized with changed variables and class names [2018-2019](Year/2018-2019/Fall/COSC/2P03/A1/) Richard and Ada, [2016-2017](Year/2017-2016/Spring/COSC/2P03/A1) by Steeve. al-Khwarizmi has submitted PPMImg.h which:w
 should be identified as having no student name/number.

  - 2P03 ([A2](Year/2018-2019/Fall/COSC/2P03/A2)) should be different between this year's students but should be matched with students from [2015-2016](Year/2015-2016/Fall/COSC/2P03/A2/)

