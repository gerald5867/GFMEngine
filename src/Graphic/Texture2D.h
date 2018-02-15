#include "Texture.h"
#include "../Utils/Types.h"
#include "../Memory/UniquePointer.h"
namespace gfm {
namespace math {
	struct Vector4D;
}//math
	class String;
namespace graphic {

	GFM_APICALL class Texture2D : public virtual Texture
	{
		public:
			using Texture2DPtr = typename memory::UniquePointer<Texture2D>;
			using int32 = utils::int32;
			using uint32 = utils::uint32;
			using Vec4 = math::Vector4D;

		public:
			virtual ~Texture2D() noexcept = default;
			
			virtual int32 GetWidth() const noexcept = 0;
			virtual int32 GetHeight() const noexcept = 0;

			virtual void UploadData(const void* pixels) = 0;
			virtual void UploadData(const Vec4& color) = 0;
			virtual void UploadData(utils::uint32 color) = 0;

		public:
			static Texture2DPtr Create(const String& filePath);
			static Texture2DPtr Create(const String& filePath, const TextureOptions& options);
			static Texture2DPtr Create(uint32 width, uint32 height, TextureFormat format);
			static Texture2DPtr Create(uint32 width, uint32 height, TextureFormat format, const TextureOptions& options);

		protected:
			Texture2D() = default;
	};

}// graphic
}// gfm