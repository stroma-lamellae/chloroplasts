import { Match, Package } from "./package";
import { File } from "./file";

export class ResultSet {
    assingmentName: string;
    courseCode: string;
    programCode: string;
    matches: Match[];
    files: File[];
}