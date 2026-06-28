package script.adv_msion
{
   import flash.display.MovieClip;
   import script.icon_item.nut_icon_item;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol15")]
   public class anm_rew_bg extends MovieClip
   {
      
      internal static const CCD_ARABIC_ITEM_ICON_POS_X:Number = 635;
      
      public var dmy_item:nut_tex00;
      
      public var mc_item:nut_icon_item;
      
      private var m_item:MovieClip = null;
      
      private var m_dmy:MovieClip = null;
      
      public function anm_rew_bg()
      {
         super();
         this.m_item = this["mc_item"];
         this.m_dmy = this["dmy_item"];
      }
      
      public function ChangeArabicLayout() : *
      {
         if(this.m_item != null && this.m_dmy != null)
         {
            this.m_item.x = CCD_ARABIC_ITEM_ICON_POS_X;
            this.m_dmy.x = CCD_ARABIC_ITEM_ICON_POS_X;
         }
      }
   }
}

