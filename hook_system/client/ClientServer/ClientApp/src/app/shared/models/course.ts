export class Assignment {
    assignmentId: number;
    name: string;
    courseId: number;
    openDate: Date;
    closeDate: Date;
    status: boolean;
    course: Course;
}

export class Course {
    courseId: number;
    userId: number;
    year: number;
    semester: number;
    programCode: string;
    courseCode: string;

    assignments: Assignment[];
}