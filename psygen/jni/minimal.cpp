#include <jni.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <android/sensor.h>
#include <android_native_app_glue.h>

#include "Engine/AndroidLogger.hpp"
#include "Square.hpp"


static const int32_t VERTEX_SIZE = sizeof(GLfloat) * 7;
static const int32_t POSITION_PARAMETER_INDEX = 0;
static const int32_t POSITION_NUM_ELEMENTS = 3;
static const int32_t COLOR_PARAMETER_INDEX = 1;
static const int32_t COLOR_NUM_ELEMENTS = 4;
static const int32_t QUAD_NUM_VERTICES = 6;


GLuint LoadShader(const char *shaderSrc, GLenum type)
{
	GLuint shader;
	GLint compiled;

	shader = glCreateShader(type);
	if (shader != 0)
	{
		glShaderSource(shader, 1, &shaderSrc, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (!compiled)
		{
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen > 1)
			{
				char* infoLog = new char[infoLen];
				glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
				psy::sg_logger(psy::Logger::WARNING, "Error compiling shader:");
				delete[] infoLog;
			}
			glDeleteShader(shader);
			shader = 0;
		}
	}
	return shader;
}



struct engine
{
	struct android_app* app;

	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	int32_t programObject;
	float width;
	float height;
};



static int engine_init_display(struct engine* engine)
{
	const EGLint attribs[] =
	{
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_BLUE_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8,
			EGL_NONE
	};

	EGLint w, h, dummy, format;
	EGLint numConfigs;
	EGLConfig config;
	EGLSurface surface;
	EGLContext context;

	EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	eglInitialize(display, NULL, NULL);
	eglChooseConfig(display, attribs, &config, 1, &numConfigs);
	eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);

	surface = eglCreateWindowSurface(display, config, engine->app->window, NULL);

	EGLint contextAttribs[] =
	{
			EGL_CONTEXT_CLIENT_VERSION, 2,
			EGL_NONE
	};
	context = eglCreateContext(display, config, NULL, contextAttribs);

	if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
	{
        psy::sg_logger(psy::Logger::WARNING, std::string("Unable to eglMakeCurrent"));
		return -1;
	}

	eglQuerySurface(display, surface, EGL_WIDTH, &w);
	eglQuerySurface(display, surface, EGL_HEIGHT, &h);

	engine->display = display;
	engine->context = context;
	engine->surface = surface;
	engine->width = w;
	engine->height = h;

	glViewport(0, 0, w, h);

	// Initialize GL state.
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);



	char vShaderStr[] =
			"attribute vec4 a_vPosition;   \n"
			"attribute vec4 a_vColor;	   \n"
			"varying vec4 v_vColor;		   \n"
			"void main()                   \n"
			"{                             \n"
			"   gl_Position = a_vPosition; \n"
			"	v_vColor = a_vColor;       \n"
			"}                             \n";

	char fShaderStr[] =
			"precision mediump float;                   \n"
			"varying vec4 v_vColor;		 				\n"
			"void main()                                \n"
			"{                                          \n"
			"  gl_FragColor = v_vColor;					\n"
			"}                                          \n";

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint programObject;
	GLint linked;

	vertexShader   = LoadShader(vShaderStr, GL_VERTEX_SHADER);
	fragmentShader = LoadShader(fShaderStr, GL_FRAGMENT_SHADER);

	engine->programObject = glCreateProgram();
	if (engine->programObject == 0)
	{
		return -1;
	}

	glAttachShader(engine->programObject, vertexShader);
	glAttachShader(engine->programObject, fragmentShader);

	glBindAttribLocation(engine->programObject, 0, "a_vPosition");
	glBindAttribLocation(engine->programObject, 1, "a_vColor");

	glLinkProgram(engine->programObject);
	glGetProgramiv(engine->programObject, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		GLint infoLen = 0;
		glGetProgramiv(engine->programObject, GL_INFO_LOG_LENGTH, &infoLen);

		if(infoLen > 1)
		{
			char* infoLog = new char[infoLen];
			glGetProgramInfoLog(engine->programObject, infoLen, NULL, infoLog);
			psy::sg_logger(psy::Logger::WARNING, "Error linking program");

			delete[] infoLog;
		}

		glDeleteProgram(engine->programObject);
		return -1;
	}

	return 0;
}



static void engine_draw_frame(struct engine* engine)
{
	if (engine->display == NULL)
	{
		// No display.
		return;
	}

	glViewport(0, 0, static_cast<int32_t>(engine->width), static_cast<int32_t>(engine->height));

	// Just fill the screen with a color.
	glClearColor(0.95f, 0.95f, 0.95f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Use the program object
	glUseProgram(engine->programObject);

	glEnableVertexAttribArray(POSITION_PARAMETER_INDEX);
	glEnableVertexAttribArray(COLOR_PARAMETER_INDEX);


	float left = -0.5f;
	float right = 0.5f;
	float top  = 0.5f;
	float bottom = -0.5f;
	float z      = 0.0f;
	const float color[] = {1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat vertices[] = {left,  top,    z, color[0], color[1], color[2], color[3],
                          left,  bottom, z, color[0], color[1], color[2], color[3],
                          right, top,    z, color[0], color[1], color[2], color[3],
                          right, top,    z, color[0], color[1], color[2], color[3],
                          left,  bottom, z, color[0], color[1], color[2], color[3],
                          right, bottom, z, color[0], color[1], color[2], color[3]};

	glVertexAttribPointer(POSITION_PARAMETER_INDEX, POSITION_NUM_ELEMENTS, GL_FLOAT, GL_FALSE, VERTEX_SIZE, vertices);
	glVertexAttribPointer(COLOR_PARAMETER_INDEX, COLOR_NUM_ELEMENTS, GL_FLOAT, GL_FALSE, VERTEX_SIZE, &vertices[3]);
	glDrawArrays(GL_TRIANGLES, 0, QUAD_NUM_VERTICES);

	glDisableVertexAttribArray(POSITION_PARAMETER_INDEX);
	glDisableVertexAttribArray(COLOR_PARAMETER_INDEX);

	eglSwapBuffers(engine->display, engine->surface);
}



static void engine_term_display(struct engine* engine)
{
	if (engine->display != EGL_NO_DISPLAY)
	{
		eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if (engine->context != EGL_NO_CONTEXT)
		{
			eglDestroyContext(engine->display, engine->context);
		}
		if (engine->surface != EGL_NO_SURFACE)
		{
			eglDestroySurface(engine->display, engine->surface);
		}
		eglTerminate(engine->display);
	}
	engine->display = EGL_NO_DISPLAY;
	engine->context = EGL_NO_CONTEXT;
	engine->surface = EGL_NO_SURFACE;
}



static void engine_handle_cmd(struct android_app* app, int32_t cmd)
{
	struct engine* engine = static_cast<struct engine*>(app->userData);
	switch (cmd)
	{

	// The window is being shown, get it ready.
	case APP_CMD_INIT_WINDOW:
		if (app->window != NULL) engine_init_display(engine);
		break;

    // The window is being hidden or closed, clean it up.
	case APP_CMD_TERM_WINDOW:
		engine_term_display(engine);
		break;
	}
}



void android_main(struct android_app* app)
{
	// Make sure glue isn't stripped.
	app_dummy();

	psy::AndroidLogger android_logger("psygen");
	Square square;

	struct engine engine;

	app->userData = &engine;
	app->onAppCmd = engine_handle_cmd;

	engine.app = app;

    bool running = true;
	while (running)
	{
		int events;
		struct android_poll_source* source;
		while ((ALooper_pollAll(0, NULL, &events, reinterpret_cast<void**>(&source))) >= 0)
			if (source) source->process(app, source);

		engine_draw_frame(&engine);
		//if (engine.display)
		//{
        //    square.draw();
        //    eglSwapBuffers(engine.display, engine.surface);
		//}

        if (app->destroyRequested) running = false;
	}

	engine_term_display(&engine);
}
