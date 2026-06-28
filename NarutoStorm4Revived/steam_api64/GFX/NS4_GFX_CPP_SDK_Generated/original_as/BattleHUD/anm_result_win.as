package script.net_cmn
{
   import flash.display.MovieClip;
   import script.icon_result.smb_btl;
   import script.icon_result.smb_win;
   import script.xcmn_menu.nut_base4;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol24")]
   public class anm_result_win extends MovieClip
   {
      
      public var mc_base_4_1:nut_base4;
      
      public var mc_base_4_2:nut_base4;
      
      public var mc_btl:smb_btl;
      
      public var mc_win:script.icon_result.smb_win;
      
      private var m_isChangedLayout:Boolean = false;
      
      public function anm_result_win()
      {
         super();
      }
      
      public function ChangeArabicLayout() : *
      {
         var _loc1_:MovieClip = null;
         var _loc2_:MovieClip = null;
         var _loc3_:MovieClip = null;
         var _loc4_:MovieClip = null;
         if(this.m_isChangedLayout == false)
         {
            _loc1_ = this["mc_btl"];
            _loc2_ = this["mc_win"];
            _loc3_ = this["mc_base_4_1"];
            _loc4_ = this["mc_base_4_2"];
            _loc1_.x += (_loc3_.x - _loc1_.x) * 2;
            _loc2_.x += (_loc4_.x - _loc2_.x) * 2;
            this.m_isChangedLayout = true;
         }
      }
   }
}

