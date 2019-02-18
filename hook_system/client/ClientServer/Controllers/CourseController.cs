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
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Course>>> GetCourses()
        {
            return await _context.Courses.ToListAsync();
        }

        // GET: api/course/#
        [HttpGet("{id}")]
        public async Task<ActionResult<Course>> GetCourse(long id)
        {
            var course = await (_context.Courses.FindAsync(id));

            // Enable below to do load sublist
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
            _context.Courses.Add(course);
            await _context.SaveChangesAsync();

            return CreatedAtAction(nameof(GetCourse), new { id = course.CourseId }, course);
        }

        // GET: api/course/#/assignments
        // Gets all of the id for a course
        [HttpGet("{id}/assignments")]
        public async Task<ActionResult<IEnumerable<long>>> GetAssignmentIds(long id)
        {
            var course = _context.Courses.Find(id);

            if (course == null)
            {
                return NotFound();
            }

            var assignments =   await (from a in _context.Assignments
                                select a).ToListAsync();
            
            var ids = assignments.Where(x => x.Course == course).Select(x => x.AssignmentId).ToList();

            return ids;
        }
    }
}