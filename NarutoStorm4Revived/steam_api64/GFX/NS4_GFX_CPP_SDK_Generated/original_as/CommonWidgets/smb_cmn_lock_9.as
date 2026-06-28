package collect_skin_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol10")]
   public dynamic class smb_cmn_lock_9 extends MovieClip
   {
      
      public var txt_title:smb_font;
      
      public function smb_cmn_lock_9()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_title.SetTextColor(15645033);
         this.txt_title.SetTextSize(30);
         this.txt_title.SetText("100/100");
      }
   }
}

