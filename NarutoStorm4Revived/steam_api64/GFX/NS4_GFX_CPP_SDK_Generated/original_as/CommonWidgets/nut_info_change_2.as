package info_lead_fla
{
   import flash.display.MovieClip;
   import script.d_boss_plat.nut_btn;
   import script.info_lead_lang.smb_change;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public dynamic class nut_info_change_2 extends MovieClip
   {
      
      public var mc_msg1:smb_change;
      
      public var mc_sprt:MovieClip;
      
      public var mc_btn:nut_btn;
      
      public function nut_info_change_2()
      {
         super();
         addFrameScript(0,this.frame1,59,this.frame60,66,this.frame67,91,this.frame92);
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
      
      internal function frame60() : *
      {
         gotoAndPlay("loop");
      }
      
      internal function frame67() : *
      {
         this.stop();
      }
      
      internal function frame92() : *
      {
         this.stop();
      }
   }
}

