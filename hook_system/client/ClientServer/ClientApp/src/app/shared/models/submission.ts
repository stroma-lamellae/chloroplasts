import { File } from '../../shared/models/file';

export class Submission {
    submissionId: number;
    assignmentId: number;
    studentNumber: string;
    studentLastname: string;
    studentFirstname: string;
    files: FileList;
    viewFiles: File[];
}
