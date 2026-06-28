package start_memory_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_win4.smb_win4;
   import script.xct_base1.nut_base1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol20")]
   public dynamic class smb_char_bg_32 extends MovieClip
   {
      
      public var mc_tex:nut_base1;
      
      public var mc_win:smb_win4;
      
      public var txt_title:smb_font;
      
      public function smb_char_bg_32()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

