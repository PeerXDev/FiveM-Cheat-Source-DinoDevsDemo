#pragma once
#include <Wallhack.h>

namespace Wallhack
{
	void Wallhack( )
	{
		if ( Variables::ESP::Enable )
		{
			uintptr_t pedinterface = *(uintptr_t*) ( Offsets::g_replayinterface + 0x18 );

			for ( int i = 0; i < 255; i++ )
			{
				uintptr_t pedlist = *(uintptr_t*) ( pedinterface + 0x100 );
				uintptr_t CPed = *(uintptr_t*) ( pedlist + ( i * 0x10 ) );   if ( !CPed ) continue;
				if ( CPed == Offsets::g_localplayer ) continue;

				Vectors::Vec3 PedPosVec3 = SDK::Players::VisualPos( CPed );

				Vectors::Vec2 PedPos = CMath::WorldToScreen( PedPosVec3 );
			 	
				Vectors::Vec2 RFoot = CMath::GetBoneWorldToScreen( CPed , 0xCC4D );
				Vectors::Vec2 Head = CMath::GetBoneWorldToScreen( CPed , 0x796E );
				float health = *(float*) ( CPed + 0x280 ) - 100;
				float between = RFoot.y / 1;
				float h = ( Head.y - between ) * 1.1;
				float w = ( h / 2 );
				float distancebetween = w / 16; 
			    

				if ( Variables::ESP::Box )
				{
					Renderer::DrawRect( Vectors::Vec2( PedPos.x - w / 2 , PedPos.y - h / 2 ) , Vectors::Vec2( PedPos.x + w / 2 , PedPos.y + h / 2 ) , ImColor( 255 , 255 , 255 , 255 ) , 0 );
				}
				if ( Variables::ESP::Skeleton )
				{
					Vectors::Vec2 Head = CMath::GetBoneWorldToScreen( CPed , 0x796E );
					Vectors::Vec2 Neck = CMath::GetBoneWorldToScreen( CPed , 0x9995 );
					Vectors::Vec2 LUperarm = CMath::GetBoneWorldToScreen( CPed , 0xB1C5 );
					Vectors::Vec2 LForearm = CMath::GetBoneWorldToScreen( CPed , 0xEEEB );
					Vectors::Vec2 RUperarm = CMath::GetBoneWorldToScreen( CPed , 0x9D4D );
					Vectors::Vec2 RForearm = CMath::GetBoneWorldToScreen( CPed , 0x6E5C );
					Vectors::Vec2 Pelvis = CMath::GetBoneWorldToScreen( CPed , 0x2E28 );
					Vectors::Vec2 LThight = CMath::GetBoneWorldToScreen( CPed , 0xE39F );
					Vectors::Vec2 LCalf = CMath::GetBoneWorldToScreen( CPed , 0xF9BB );
					Vectors::Vec2 LFoot = CMath::GetBoneWorldToScreen( CPed , 0x3779 );
					Vectors::Vec2 RThight = CMath::GetBoneWorldToScreen( CPed , 0xCA72 );
					Vectors::Vec2 RCalf = CMath::GetBoneWorldToScreen( CPed , 0x9000 );
					Vectors::Vec2 RFoot = CMath::GetBoneWorldToScreen( CPed , 0xCC4D );
					Vectors::Vec2 RHand = CMath::GetBoneWorldToScreen( CPed , 0xdead );
					Vectors::Vec2 LHand = CMath::GetBoneWorldToScreen( CPed , 0x49d9 );	
					Renderer::DrawLine( Head , Neck , ImColor( 255 , 255 , 255 ) );
					Renderer::DrawLine( Neck , LUperarm , ImColor( 255 , 255 , 255 ) );
					Renderer::DrawLine( LUperarm , LForearm , ImColor( 255 , 255 , 255 ) );
					Renderer::DrawLine( LForearm , LHand , ImColor( 255 , 255 , 255 ) );
					Renderer::DrawLine( Neck , RUperarm , ImColor( 255 , 255 , 255 ) );
					Renderer::DrawLine( RUperarm , RForearm , ImColor( 255 , 255 , 255 ) );
					Renderer::DrawLine( RForearm , RHand , ImColor( 255 , 255 , 255 ) );
					Renderer::DrawLine( Neck , Pelvis , ImColor( 255 , 255 , 255 ) );
					Renderer::DrawLine( Pelvis , LThight , ImColor( 255 , 255 , 255 ) );
					Renderer::DrawLine( LThight , LCalf , ImColor( 255 , 255 , 255 ) );
					Renderer::DrawLine( LCalf , LFoot , ImColor( 255 , 255 , 255 ) );
					Renderer::DrawLine( Pelvis , RThight , ImColor( 255 , 255 , 255 ) );
					Renderer::DrawLine( RThight , RCalf , ImColor( 255 , 255 , 255 ) );
					Renderer::DrawLine( RCalf , RFoot , ImColor( 255 , 255 , 255 ) );
				}	
				if ( Variables::ESP::Healthbar )
				{
					if ( health > 0 )
					{
						float Healthmath = ( h / 100 ) * health;
						Renderer::DrawHealthBar( Vectors::Vec2( ( PedPos.x + w / 2 ) + distancebetween , PedPos.y + h / 2 ) , Vectors::Vec2( 2 , h / 100 * 100 ) , ImColor( 0 , 0 , 0 , 255 ) );
						Renderer::DrawHealthBar( Vectors::Vec2( ( PedPos.x + w / 2 ) + distancebetween , PedPos.y + h / 2 ) , Vectors::Vec2( 2 , Healthmath ) , ImColor( 0 , 255 , 0 ) );
					}
				}
				if ( Variables::ESP::Snaplines )
				{
					Vectors::Vec2 Localplayersex = CMath::GetBoneWorldToScreen( Offsets::g_localplayer , 0x2E28 );

					Renderer::DrawLine( { Localplayersex.x, Localplayersex.y } , { PedPos.x, PedPos.y } , ImColor( 255 , 255 , 255 ) , 1 );
				}
			}
		}
	}
}