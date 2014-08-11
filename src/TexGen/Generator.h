#pragma once

#include <TexGen/Node.h>
#include <TexGen/Texture.h>
#include <TexGen/Operations/Operation.h>
#include <map>
#include <string>
#include <cassert>

enum eBlendMode
{
	kBlendMode_Undefined = 0,
	kBlendMode_Add,
	kBlendMode_Multiply
};

class Generator
{
public:
   Generator( void );
   ~Generator( void );

   void Initialize( Node* inProgramNode );

   void Run( void );

   void Destroy( void );

   void RegisterOperation( const std::string& inOperationName, Operation* inOperation );

   inline bool HasTexture( const std::string& inTextureName ) const { return mTextures.find( inTextureName ) != mTextures.end(); }
   inline Texture* GetTexture( const std::string& inTextureName ) const { assert( HasTexture( inTextureName ) ); return mTextures.at(inTextureName); }

private:
   std::map<std::string, Texture*> mTextures;
   std::map<std::string, Operation*> mOperations;
   Node* mProgramNode;

   eBlendMode mBlendMode;
};
