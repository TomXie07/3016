
#include "public.h"
#include "teapot.h"

//
// global variable
//

#define DELAY 16    // timer delay time

vec2 screen = vec2(1024, 576);

vec2 mouse;
vec2 lastpos;
int mouse_button = -1;

// camera control
bool ctrlCamera = true;
vec3 viewRotation = vec3(25.0f, 0.0f, 0.0f);
float viewDistance = -10.0f;

float teapot_rot = 0.0f;
float teapot_lid_pos = 0.0f;

struct Particle
{
    vec3 position;
    vec3 velocity;
};

std::vector<Particle> particles;

//
// functions
//

void init(void);
void reshape(int w, int h);
void keydown(unsigned char key, int x, int y);
void keyup(unsigned char key, int x, int y);
void special_keydown(int key, int x, int y);
void special_keyup(int key, int x, int y);
void mouse_event(int button, int state, int x, int y);
void mouse_motion(int x, int y);
void mouse_move(int x, int y);
void timer(int arg);
void display(void);

// main
int main(int argc, char* argv[])
{
    // init glut
    glutInit(&argc, argv);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("glut - OpenGL");

    // events callback
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keydown);
    glutKeyboardUpFunc(keyup);
    glutSpecialFunc(special_keydown);
    glutSpecialUpFunc(special_keyup);
    glutMouseFunc(mouse_event);
    glutMotionFunc(mouse_motion);
    glutPassiveMotionFunc(mouse_move);
    glutTimerFunc(DELAY, timer, DELAY);
    glutDisplayFunc(display);

    init();

    // main loop
    glutMainLoop();

    // free resources

    return 0;
}

void init_lights()
{
    // direction light
    GLfloat light_position[] = { 20.0f, 20.0f, 20.0f, 0.0f };
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    //glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // set material
    GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 16.0f);

    glEnable(GL_NORMALIZE);
}

void vertex_begin(const Vertex* vs)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &vs->position);
    glNormalPointer(GL_FLOAT, sizeof(Vertex), &vs->normal);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &vs->texcoord);
}

void vertex_end(const Vertex* vs)
{
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void draw_arrays(int shape, const Vertex* vs, size_t pos, size_t size)
{
    vertex_begin(vs);
    glDrawArrays(shape, GLint(pos), GLsizei(size));
    vertex_end(vs);
}

void draw_elements(int shape, const Vertex* vs, const GLuint* indices, size_t size)
{
    vertex_begin(vs);
    glDrawElements(shape, GLsizei(size), GL_UNSIGNED_INT, indices);
    vertex_end(vs);
}

void init(void)
{
    // clear color
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);

    // shade model
    glShadeModel(GL_SMOOTH);

    // enable blend
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // enable depth test
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);

    // lighting
    init_lights();

    // enable texture 2D
    glEnable(GL_TEXTURE_2D);
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, double(w) / double(h), 1.0, 1000.0);

    glMatrixMode(GL_MODELVIEW);
}

void keydown(unsigned char key, int x, int y)
{
    switch (key) {
    case 27: // press esc to exit
        exit(EXIT_SUCCESS);
        break;
    case 32: // space
        ctrlCamera = !ctrlCamera;
        printf("control camera: %s\n", ctrlCamera ? "true" : "false");
        break;
    default:
        printf("key = %d\n", int(key));
        break;
    }
}

void keyup(unsigned char key, int x, int y)
{
}

// special key
void special_keydown(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_F1:
        break;
    case GLUT_KEY_F2:
        break;
    case GLUT_KEY_F3:
        break;
    case GLUT_KEY_F4:
        break;

    case GLUT_KEY_UP:
        /*viewDistance += 1.0f;
        if (viewDistance > -1.0f) {
            viewDistance = -1.0f;
        }*/
        teapot_lid_pos += 0.1f;
        break;
    case GLUT_KEY_DOWN:
        //viewDistance -= 1.0f;
        teapot_lid_pos -= 0.1f;
        if (teapot_lid_pos < 0.0f) {
            teapot_lid_pos = 0.0f;
        }
        break;
    case GLUT_KEY_LEFT:
        //viewRotation.y -= 1.0f;
        teapot_rot -= 1.0f;
        if (teapot_rot < 0.0f) {
            teapot_rot = 0.0f;
        }
        break;
    case GLUT_KEY_RIGHT:
        //viewRotation.y += 1.0f;
        teapot_rot += 1.0f;
        if (teapot_rot >= 30.0f) {
            teapot_rot = 30.0f;
        }
        break;
    default:
        printf("skey = %d\n", key);
        break;
    }
}

void special_keyup(int key, int x, int y)
{
}

void mouse_event(int button, int state, int x, int y)
{
    // printf("mouse %d %d %d %d\n", button, state, x, y);
    if (state == GLUT_DOWN) {
        lastpos = mouse;
        mouse_button = button;
        switch (button) {
        case GLUT_LEFT_BUTTON:
            break;
        case GLUT_MIDDLE_BUTTON:
            break;
        case GLUT_RIGHT_BUTTON:
            break;
        default:
            break;
        }
    }
    else if (state == GLUT_UP) {
        switch (button) {
        case GLUT_LEFT_BUTTON:
            break;
        case GLUT_MIDDLE_BUTTON:
            break;
        case GLUT_RIGHT_BUTTON:
            break;
        default:
            break;
        }
        mouse_button = -1;
    }
}

void mouse_move(int x, int y)
{
    //printf("mouse move %d, %d\n", x, y);
    mouse = vec2((float) x, (float) y);

}

void mouse_motion(int x, int y)
{
    //printf("mouse motion %d, %d\n", x, y);
    mouse = vec2(x, y);

    if (ctrlCamera) {
        if (mouse_button == GLUT_LEFT_BUTTON) { // left button
            vec2 offset = mouse - lastpos;
            offset = offset * 0.05f;
            // cout << offset.x << ", " << offset.y << endl;

            viewRotation.x += offset.y;
            viewRotation.y += offset.x;

            lastpos = mouse;
        }
        else if (mouse_button == GLUT_RIGHT_BUTTON) { // right button
            vec2 offset = mouse - lastpos;
            offset = offset * 0.05f;
            viewDistance += offset.y;

            lastpos = mouse;
        }
    }
    else {
        if (mouse_button == GLUT_LEFT_BUTTON) { // left button
            vec2 offset = mouse - lastpos;
            offset = offset * 0.05f;
            // cout << offset.x << ", " << offset.y << endl;

            int mod = glutGetModifiers();
            if (mod & GLUT_ACTIVE_CTRL) {
                teapot_lid_pos -= offset.y;
                if (teapot_lid_pos < 0.0f) {
                    teapot_lid_pos = 0.0f;
                }
            }
            else {
                teapot_rot += offset.y;
                if (teapot_rot < 0.0f) {
                    teapot_rot = 0.0f;
                }
                else if (teapot_rot >= 30.0f) {
                    teapot_rot = 30.0f;
                }
            }

            lastpos = mouse;
        }
    }
}

void timer(int arg)
{
    float delay = arg * 0.001f;

    // add particle
    if (teapot_rot >= 30.0f) {
        Particle p;
        p.position = vec3(4.0f, 0.6f, 0.0f);
        p.velocity = vec3(1.0f, 1.0f, 0.0f);
        p.velocity.x += random_real(-1.0f, 1.0f) * 0.2f;
        p.velocity.z += random_real(-1.0f, 1.0f) * 0.2f;
        particles.push_back(p);
    }

    // process paricles
    for (auto itr = particles.begin(); itr != particles.end();) {
        itr->position += itr->velocity * delay;
        itr->velocity.y -= 9.8f * delay;
        if (itr->position.y < -5.0f) {
            itr = particles.erase(itr);
        }
        else {
            ++itr;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(arg, timer, arg);
}

void display(void)
{
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glLoadIdentity();

    // camera
    glTranslatef(0.0f, 0.0f, viewDistance);
    glRotatef(viewRotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(viewRotation.y, 0.0f, 1.0f, 0.0f);

    // draw teapot
    glPushMatrix();
    glRotatef(-teapot_rot, 0.0f, 0.0f, 1.0f);
    draw_arrays(GL_TRIANGLES, TEAPOT_BODY, 0, ARRAYSIZE(TEAPOT_BODY));

    glPushMatrix();
    glTranslatef(0.0f, teapot_lid_pos, 0.0f);
    draw_arrays(GL_TRIANGLES, TEAPOT_LID, 0, ARRAYSIZE(TEAPOT_LID));
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    //glTranslatef(3.0f, 2.5f, 0.0f);
    glTranslatef(4.0f, 0.5f, 0.0f);
    //glutSolidCube(0.5f);
    glPopMatrix();

    // draw water
    for (auto& p : particles) {
        glPushMatrix();
        glTranslatef(p.position.x, p.position.y, p.position.z);
        glScalef(0.1f, 0.1f, 0.1f);
        //glutSolidCube(0.1f);
        glutSolidSphere(1.0f, 16, 16);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 0.0f);
    glScalef(10.0f, 0.1f, 10.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // swap buffer and display
    glutSwapBuffers();
}
