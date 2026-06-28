package map_l_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol17")]
   public dynamic class smb_memory_8 extends MovieClip
   {
      
      public var dmy_memory:nut_tex00;
      
      public var txt_memory:smb_font;
      
      public function smb_memory_8()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_memory.SetTextSize(25);
         this.txt_memory.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_memory.SetTextPivot(smb_font.CCD_PIVOT_LC);
      }
   }
}

