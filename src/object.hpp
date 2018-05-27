
class Object{
	private: 
		int ObjectID;
		int locX;
		int locY;
		
		std::vector <glm::vec3> vertices;
		std::vector <glm::vec2> uvs;
		std::vector <glm::vec3> normals; 

		GLuint NormalTexture;
		GLuint Texture;
		glm::mat4 Model;
		glm::mat4 Translate;

		GLuint vertexbuffer;
		GLuint uvbuffer;
		GLuint normalbuffer;

		// Shader Parameters
		GLuint programID;
		GLuint Vertex;
		GLuint TextureID;
		GLuint NormalTextureID;
		GLuint vertexUV;
		GLuint normalHandler;

		GLuint MatrixID;
		GLuint ViewMatrixID;
		GLuint ModelMatrixID;
		GLuint mv3x3ID;
		GLuint LightID;
	public:
		Object( const char * objpath,
				const char * texturepath,
				const char * normaltexturepath,
				const char * vertexshader,
				const char * fragmentshader,
				int, int);
		bool loadOBJ(const char * path);
		bool render(glm::mat4,glm::mat4,glm::vec3);
		bool InitShaders(const char * vertex_file_path, const char * fragment_file_path);
		bool setMatrices();
		bool InitBuffers();
		bool Animate();
		~Object();
};
