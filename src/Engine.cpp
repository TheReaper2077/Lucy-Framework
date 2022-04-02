#include "Engine.h"

#include "Lucy/Lucy.h"

void Engine::Init() {
	assert(glfwInit());

	window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	glfwMakeContextCurrent(window);
	
	assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

	glEnable(GL_LINE_SMOOTH);

	glViewport(0, 0, WIDTH, HEIGHT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);

	glfwSetWindowPos(window, 50, 50);
	glfwSetKeyCallback(window, lf::Events::Key::Callback);
	glfwSetKeyCallback(window, lf::CameraKeyCallback);
	glfwSetCursorPosCallback(window, lf::Events::Mouse::CursorPosCallback);
	glfwSetCursorPosCallback(window, lf::CameraMouseCursorPosCallback);
	glfwSetMouseButtonCallback(window, lf::Events::Mouse::Callback);

	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigDockingWithShift = true;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 400");

	// glGenFramebuffers(1, &framebuffer);
	// glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// glGenTextures(1, &textureColorbuffer);
	// glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// glBindTexture(GL_TEXTURE_2D, 0);

	// // attach it to currently bound framebuffer object
	// glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0); 

	// unsigned int rbo;
	// glGenRenderbuffers(1, &rbo);
	// glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
	// glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);  
	// glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	// assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	// glBindFramebuffer(GL_FRAMEBUFFER, 0);

	for (auto& layer: layers) {
		layer->SetWindow(window);
		layer->Init();
	}
}

// bool show_demo_window = false;

void Engine::Mainloop() {
	while (!glfwWindowShouldClose(window)) {
		const auto& start_time = std::chrono::high_resolution_clock::now();
		
		ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

		glEnable(GL_DEPTH_TEST);

		// glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		glfwPollEvents();
		glClearColor(0.2, 0.2, 0.2, 0.2);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto& layer: layers) {
			layer->Update(dt);
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		glfwSwapBuffers(window);

		const auto& end_time = std::chrono::high_resolution_clock::now();
		dt = std::chrono::duration<double, std::ratio<1, 60>>(end_time - start_time).count();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}
