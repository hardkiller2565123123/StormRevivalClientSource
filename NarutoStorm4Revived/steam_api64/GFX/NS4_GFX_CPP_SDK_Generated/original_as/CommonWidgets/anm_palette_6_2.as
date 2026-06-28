package start_ning_fla
{
   import flash.display.MovieClip;
   import script.duel_item.nut_palet;
   import script.xcmn_btn_plat.all_btn_plat;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol20")]
   public dynamic class anm_palette_6 extends MovieClip
   {
      
      public var mc_frame:MovieClip;
      
      public var mc_palette:nut_palet;
      
      public var mc_palette_btn:all_btn_plat;
      
      public var mc_palette_sel:MovieClip;
      
      public function anm_palette_6()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
      
      internal function frame2() : *
      {
         stop();
      }
      
      internal function frame3() : *
      {
         this.stop();
      }
   }
}

