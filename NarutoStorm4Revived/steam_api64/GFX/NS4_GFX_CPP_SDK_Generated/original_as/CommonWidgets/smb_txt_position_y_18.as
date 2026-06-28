package option_keyboard_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public dynamic class smb_txt_position_y_18 extends MovieClip
   {
      
      public var txt_position_y2:smb_font;
      
      public var txt_position_y1:smb_font;
      
      public function smb_txt_position_y_18()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_position_y1.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_position_y1.SetTextSize(smb_font.CCD_FONT_SIZE_LARGE);
         this.txt_position_y2.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_position_y2.SetTextSize(smb_font.CCD_FONT_SIZE_LARGE);
      }
   }
}

