package script.msg_plays
{
   import ELoader.ExtendLoader;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.net.URLRequest;
   import script.xcmn_tex00.nut_tex00;
   import script.xct_stp1.nut_stp1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public class nut_title_op extends MovieClip
   {
      
      public var all_stp1:nut_stp1;
      
      public var dmy_msg1:nut_tex00;
      
      private var m_txtDmy:MovieClip = null;
      
      private var m_txtLoader:ExtendLoader = null;
      
      public function nut_title_op()
      {
         super();
         addFrameScript(74,this.frame75,110,this.frame111);
         this.m_txtDmy = this["dmy_msg1"];
         addEventListener(Event.REMOVED_FROM_STAGE,this.onRemove);
      }
      
      public function onRemove(param1:Event) : *
      {
         if(hasEventListener(Event.ENTER_FRAME) != 0)
         {
            removeEventListener(Event.ENTER_FRAME,this.onLoadCheck);
         }
         removeEventListener(Event.REMOVED_FROM_STAGE,this.onRemove);
      }
      
      public function LoadTitle(param1:int) : *
      {
         if(this.m_txtLoader != null)
         {
            this.m_txtDmy.removeChild(this.m_txtLoader);
            if(hasEventListener(Event.ENTER_FRAME) != 0)
            {
               removeEventListener(Event.ENTER_FRAME,this.onLoadCheck);
            }
         }
         this.m_txtLoader = new ExtendLoader();
         this.m_txtDmy.addChild(this.m_txtLoader);
         var _loc2_:URLRequest = null;
         switch(param1)
         {
            case all_nut.CCD_TEXT_MSG_ADV_1:
               _loc2_ = new URLRequest("./LANG/plays_adv1.xfbin");
               break;
            case all_nut.CCD_TEXT_MSG_ADV_2:
               _loc2_ = new URLRequest("./LANG/plays_adv2.xfbin");
               break;
            case all_nut.CCD_TEXT_MSG_ADV_3:
               _loc2_ = new URLRequest("./LANG/plays_adv3.xfbin");
         }
         if(_loc2_ != null)
         {
            this.m_txtLoader.load(_loc2_);
            this.m_txtLoader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
            addEventListener(Event.ENTER_FRAME,this.onLoadCheck);
         }
      }
      
      public function onLoadCheck(param1:Event) : *
      {
         if(Boolean(this.m_txtLoader) && this.m_txtLoader.IsLoadedAll() == true)
         {
            trace("LoadCompletedCallBack");
            all_nut(parent).LoadCompleted();
            removeEventListener(Event.ENTER_FRAME,this.onLoadCheck);
         }
      }
      
      internal function frame75() : *
      {
         this.stop();
      }
      
      internal function frame111() : *
      {
         this.stop();
      }
   }
}

