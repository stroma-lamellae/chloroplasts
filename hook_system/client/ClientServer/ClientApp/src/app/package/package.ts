import { Assignment } from '../course/course';

export class PreviousAssignment {
    assignmentId: number;
    packageId: number;
    assignment: Assignment;
    pack: Package;
}

export class Package {
    assignmentId: number;
    resultId: number;
    estimatedCompletion: Date;
    assignment: Assignment;
    // result: Result;
    previousAssignments: PreviousAssignment[];
}