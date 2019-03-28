using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

using ClientServer.Models;

namespace ClientServer.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class CourseController : ControllerBase
    {
        private readonly ClientServerContext _context;

        public CourseController(ClientServerContext context)
        {
            _context = context;
        }
        // GET api/course
        // Gets all of the courses
        [HttpGet()]
        public async Task<ActionResult<IEnumerable<Course>>> GetCourses()
        {
            return await _context.Course.Include(c => c.Assignments).ToListAsync();
        }

        // GET api/course/year/semester
        // Gets all of the courses in a particular year and semester
        [HttpGet("{year}/{semester}")]
        public async Task<ActionResult<IEnumerable<Course>>> GetCourses(int year, int semester)
        {
            var courses =  await _context.Course
                .Where(c => c.Year == year)
                .Where(c => c.Semester == semester)
                .Include(c => c.Assignments)
                .ToListAsync();

            return courses;
        }

        // GET: api/course/#
        [HttpGet("{id}")]
        public async Task<ActionResult<Course>> GetCourse(long id)
        {
            var course = await (_context.Course.FindAsync(id));

            // Enable below to do load sublist of assignments
            // _context.Entry(course).Collection(x => x.Assignments).Load(); 

            if (course == null)
            {
                return NotFound(); // Return 404
            }
            return course; // Return 200
        }

        // POST: api/course
        // Adds a course to the database
        [HttpPost]
        public async Task<IActionResult> PostCourse(Course course)
        {
            _context.Course.Add(course);
            await _context.SaveChangesAsync();

            return CreatedAtAction(nameof(GetCourse), new { id = course.CourseId }, course);
        }

        // PUT: api/course/{id}
        // Updates the course with the given id
        [HttpPut("{id}")]
        public async Task<IActionResult> PutCourse(long id, Course course)
        {
            if (id != course.CourseId)
            {
                return BadRequest();
            }

            _context.Entry(course).State = EntityState.Modified;
            await _context.SaveChangesAsync();

            return NoContent();
        }

        // DELETE: api/course/{id}
        // Removes a course and all of the children items
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteCourse(long id)
        {
            var course = await _context.Course.FindAsync(id);

            if (course == null)
            {
                return NotFound();
            }

            _context.Course.Remove(course);
            await _context.SaveChangesAsync();

            return NoContent();
        }

        // GET: api/course/#/assignments
        // Gets all of the assignments for a course
        [HttpGet("{id}/assignments")]
        public async Task<ActionResult<Course>> GetAssignments(long id)
        {
            // Get the assignment ids for this course
            var assignments = await _context.Course
                .Where(c => c.CourseId == id)
                .Include(c => c.Assignments)
                .FirstAsync();

            return assignments;
        }
    }
}