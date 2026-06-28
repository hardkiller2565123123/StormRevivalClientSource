package script.load_cmn
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public dynamic class nut_load_gauge00 extends MovieClip
   {
      
      public var txt_load:smb_font;
      
      public function nut_load_gauge00()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_load.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_load.SetTextSize(30);
      }
   }
}

