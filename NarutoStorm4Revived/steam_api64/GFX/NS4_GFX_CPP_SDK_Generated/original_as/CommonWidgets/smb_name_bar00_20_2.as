package freebtl_cp_fla
{
   import flash.display.MovieClip;
   import script.freebtl_namebar.nut_namebar01;
   import script.icon_rank_s_txt.nut_rank_s;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol42")]
   public dynamic class smb_name_bar00_20 extends MovieClip
   {
      
      public var all_rank_s:nut_rank_s;
      
      public var all_namebar01:nut_namebar01;
      
      public function smb_name_bar00_20()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         stop();
      }
   }
}

