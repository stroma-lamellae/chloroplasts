import { Assignment } from './course';
import { Submission } from './submission';
import { File } from './file';

export class Line {
  lineId: number;
  matchId: number;
  submissionId: number;
  lineStart: number;
  lineEnd: number;
  filePath: string;
  match: Match;
  submission: Submission;
  viewFile: File;
}

export class Match {
  matchId: number;
  resultId: number;
  lines: Line[];
}

export class Result {
  resultId: number;
  completedDate: Date;
  packageId: number;
  pack: Package;
  matches: Match[];
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
