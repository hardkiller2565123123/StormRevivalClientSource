package start_memory_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_base;
   import script.xcmn_menu.nut_base7;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol21")]
   public dynamic class smb_condition_win_33 extends MovieClip
   {
      
      public var mc_base:nut_base;
      
      public var mc_win2:nut_base7;
      
      public var txt_condition:smb_font;
      
      public var txt_title:smb_font;
      
      public function smb_condition_win_33()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_condition.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_condition.SetTextColor(smb_font.CCD_COLOR_BLACK);
      }
   }
}

