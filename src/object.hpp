
class Object{
	private: 
		int ObjectID;
		std::vector <glm::vec3> vertices;
		std::vector <glm::vec2> uvs;
		std::vector <glm::vec3> normals; 
		GLuint Texture;
		glm::mat4 Model;
		
		GLuint vertexbuffer;
		GLuint uvbuffer;
		
		// Shader Parameters
		GLuint programID;
		GLuint Vertex;
		GLuint TextureID;
		GLuint vertexUV;
		GLuint MatrixID;
	public:
		Object( const char * objpath,
				const char * texturepath,
				const char * vertexshader,
				const char * fragmentshader);
		bool loadOBJ(const char * path);
		bool render(glm::mat4,glm::mat4);
		bool loadTexture(const char * path);
		bool InitShaders(const char * vertex_file_path, const char * fragment_file_path);
		bool setMatrices();
		bool InitBuffers();
		bool Animate();
		~Object();
};
