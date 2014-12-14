//typedef GLfloat[4]  float4;
//typedef GLfloat[16] float16;
//
//void GLASM_ANDROID_RENDER(unsigned char* GLASM_PRG)
//{
//    if (GLASM_PRG)                                                                                                                                   
//    {                                                                                                                                                
//        const unsigned char* pc = GLASM_PRG;                                                                                                         
//        GLASM cmd = *((GLASM*) pc);                                                                                                                  
//                                                                                                                                                     
//                                                                                                                                                     
//        union                                                                                                                                        
//        {                                                                                                                                            
//            GLbitfield     bitfield;                                                                                                                 
//            struct { GLfloat x; GLfloat y; GLfloat z; GLfloat w } vec4;
//            GLenum         state;                                                                                                                     
//            unsigned char* addr;
//            GLuint         shader;
//            GLuint         texture;
//            struct                                                                                                                                    
//            {                                                                                                                                         
//                GLuint    handler[2];                                                                                                                 
//                GLint     num_indices;                                                                                                                
//                GLubyte   num_attr;                                                                                                                   
//                GLubyte   attr[32];                                                                                                                   
//                GLenum    primitive_type;        
//                GLubyte   stride;
//            } geometry;                                                                                                                               
//        } value;                                                                                                                                      
//                                                                                                                                                      
//                                                                                                                                                      
//        for (pc += sizeof(GLASM) ; cmd != GLASM::END ; cmd = *((GLASM*) pc), pc += sizeof(GLASM) )                                                    
//        {                                                                                                                                             
//            switch (cmd)                                                                                                                              
//            {                                                                                                                                         
//            case GLASM::CLR:                                                                                                                          
//                GLASM_NEXT(pc, GLbitfield, value.bitfield);                                                                                           
//                //PSY_LOG_DBG("        glClear(0x%X)", value.bitfield);                                                                                 
//                glClear(value.bitfield);                                                                                                          
//                break;                                                                                                                                
//                                                                                                                                                      
//                                                                                                                                                      
//            case GLASM::CCL:                                                                                                                          
//                GLASM_NEXT(pc, GLfloat[4], value.glfloat);                                                                                            
//                //GLASM_NEXT(pc, GLfloat, value.glfloat[1]);                                                                                            
//                //GLASM_NEXT(pc, GLfloat, value.glfloat[2]);                                                                                            
//                //GLASM_NEXT(pc, GLfloat, value.glfloat[3]);                                                                                            
//                //PSY_LOG_DBG("        glClearColor(%f, %f, %f, %f)", value.glfloat[0], value.glfloat[1], value.glfloat[2], value.glfloat[3]);          
//                glClearColor(value.glfloat[0], value.glfloat[1], value.glfloat[2], value.glfloat[3]);                                                 
//                break;                                                                                                                                
//                                                                                                                                               
//            case GLASM::DIS:                                                                                                                   
//                GLASM_NEXT(pc, GLenum, value.state);                                                                                           
//                //PSY_LOG_DBG("        glDisable(0x%X)", value.state);                                                                           
//                glDisable(value.state);                                                                                                        
//                break;                                                                                                                         
//                                                                                                                                               
//            case GLASM::SHD:                                                                                                                   
//                GLASM_NEXT(pc, GLuint, value.shader);                                                                                           
//                //PSY_LOG_DBG("        glUseProgram(%d)", value.shader);
//                glUseProgram(value.shader);
//                break;                                                                                                                         
//                                                                                                                                               
//            case GLASM::TEX:                                                                                                                   
//                GLASM_NEXT(pc, GLuint, value.texture);                                                                                           
//                //PSY_LOG_DBG("        glActiveTexture(%d)", value.texture);
//                glActiveTexture(value.texture);
//                break;                                                                                                                         
//                                                                                                                                               
//            case GLASM::VBO:                                                                                                                   
//                GLASM_NEXT(pc, GLuint, value.geometry.handler[0]);                                                                             
//                GLASM_NEXT(pc, GLuint, value.geometry.handler[1]);                                                                             
//                GLASM_NEXT(pc, GLint, value.geometry.num_indices);                                                                             
//                GLASM_NEXT(pc, GLubyte, value.geometry.num_attr);                                                                              
//
//                //PSY_LOG_DBG("            glBindBuffer(GL_ARRAY_BUFFER, %d);", value.geometry.handler[0]);                                                    
//                //PSY_LOG_DBG("            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, %d);", value.geometry.handler[1]);
//                glBindBuffer(GL_ARRAY_BUFFER, value.geometry.handler[0]);
//                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, value.geometry.handler[1]);
//                
//                value.geometry.stride = 0;
//                for (GLubyte i=0 ; i<value.geometry.num_attr ; ++i)
//                {                                                                                                                              
//                    GLASM_NEXT(pc, GLubyte, value.geometry.attr[i]);                                                                           
//                    value.geometry.stride += value.geometry.attr[i];
//                }                                                                                                                              
//                value.geometry.stride *= sizeof(GLfloat);
//
//                for (int i=0 , p=0 ; i<value.geometry.num_attr ; p += value.geometry.attr[i]*sizeof(GLfloat) , ++i)                            
//                {                                                                                                                              
//                    //PSY_LOG_DBG("            glEnableVertexAttribArray(%d);", i);                                                        
//                    //PSY_LOG_DBG("            glVertexAttribPointer(%d, %d, GL_FLOAT, GL_FALSE, %d, (const void*)%d);", i, value.geometry.attr[i], value.geometry.stride, p);
//                    glEnableVertexAttribArray(i);
//                    glVertexAttribPointer(i, value.geometry.attr[i], GL_FLOAT, GL_FALSE, value.geometry.stride, (const void*)p);
//                }                                                                                                                              
//                
//                GLASM_NEXT(pc, GLenum, value.geometry.primitive_type);                                                                         
//
//                //PSY_LOG_DBG("            glDrawElements(%d, %d, GL_UNSIGNED_SHORT, 0);", value.geometry.primitive_type, value.geometry.num_indices);
//                glDrawElements(value.geometry.primitive_type, value.geometry.num_indices, GL_UNSIGNED_SHORT, 0);
//
//                for (GLubyte i=0 ; i<value.geometry.num_attr ; ++i)                                                                            
//                {                                                                                                                              
//                    //PSY_LOG_DBG("            glDisableVertexAttribArray(%d);", i);
//                    glDisableVertexAttribArray(i);
//                }                                                                                                                              
//                break;                                                                                                                         
//                                                                                                                                               
//            case GLASM::VWP:                                                                                                                   
//                GLASM_NEXT(pc, GLint, value.glint[0]);                                                                                         
//                GLASM_NEXT(pc, GLint, value.glint[1]);                                                                                         
//                GLASM_NEXT(pc, GLint, value.glint[2]);                                                                                         
//                GLASM_NEXT(pc, GLint, value.glint[3]);                                                                                         
//                //PSY_LOG_DBG("        glViewport(%d, %d, %d, %d)", value.glint[0], value.glint[1], value.glint[2], value.glint[3]);             
//                glViewport(value.glint[0], value.glint[1], value.glint[2], value.glint[3]);                                                    
//                break;                                                                                                                         
//                                                                                                                                               
//                                                                                                                                               
//                                                                                                                                               
//            case GLASM::JMP:                                                                                                                   
//                GLASM_NEXT(pc, unsigned char*, value.addr);                                                                                    
//                //PSY_LOG_DBG("        JMP %p", value.addr);                                                                                     
//                /*pc = value.addr;*/                                                                                                           
//                break;                                                                                                                         
//                                                                                                                                               
//            default:                                                                                                                           
//                break;                                                                                                                         
//            }                                                                                                                                  
//        }                                                                                                                                      
//    }
//}
