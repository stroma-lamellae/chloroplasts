import { Assignment } from './course';

export class Result {
  resultId: number;
  completedDate: Date;
  packageId: number;
  pack: Package;
  // matches: Match[];
}

export class PreviousAssignment {
  assignmentId: number;
  packageId: number;
  assignment: Assignment;
  pack: Package;
}

export class Package {
  packageId: number;
  assignmentId: number;
  estimatedCompletion: Date;
  assignment: Assignment;
  result: Result;
  previousAssignments: PreviousAssignment[];
}
