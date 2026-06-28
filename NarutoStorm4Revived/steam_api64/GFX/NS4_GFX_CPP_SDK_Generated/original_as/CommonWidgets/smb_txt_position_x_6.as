package option_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol35")]
   public dynamic class smb_txt_position_x_6 extends MovieClip
   {
      
      public var txt_position_x1:smb_font;
      
      public var txt_position_x2:smb_font;
      
      public function smb_txt_position_x_6()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_position_x1.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_position_x1.SetTextSize(smb_font.CCD_FONT_SIZE_LARGE);
         this.txt_position_x2.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_position_x2.SetTextSize(smb_font.CCD_FONT_SIZE_LARGE);
      }
   }
}

