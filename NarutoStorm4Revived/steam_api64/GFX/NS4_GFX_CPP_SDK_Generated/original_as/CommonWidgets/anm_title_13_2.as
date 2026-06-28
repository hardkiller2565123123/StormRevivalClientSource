package map_sm_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_base;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol61")]
   public dynamic class anm_title_13 extends MovieClip
   {
      
      public var all_base:nut_base;
      
      public var txt_title:smb_font;
      
      public function anm_title_13()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_title.SetTextSize(33);
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

