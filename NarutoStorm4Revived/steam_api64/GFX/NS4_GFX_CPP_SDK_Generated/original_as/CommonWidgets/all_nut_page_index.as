package script.duel_cutin4
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol18")]
   public class all_nut_page_index extends MovieClip
   {
      
      public var all_link1:nut_link1;
      
      public var all_link2:nut_link2;
      
      public var all_link3:nut_link3;
      
      private var m_anmList:Array = [];
      
      private var m_phase:int;
      
      public function all_nut_page_index()
      {
         super();
         m_anmList.push(all_link1,all_link2,all_link3);
         for each(var clip in m_anmList)
         {
            clip.stop();
            clip.visible = false;
         }
      }
      
      public function PlayAnm(idx:int) : void
      {
         if(idx < 0 || idx >= m_anmList.length)
         {
            return;
         }
         m_phase = idx;
         for each(var c in m_anmList)
         {
            c.stop();
            c.visible = false;
         }
         var show:MovieClip = m_anmList[m_phase];
         show.visible = true;
         show.gotoAndPlay("in");
         show.addEventListener(Event.ENTER_FRAME,onEnterFrame);
      }
      
      private function onEnterFrame(e:Event) : void
      {
         var clip:MovieClip = m_anmList[m_phase];
         if(clip.currentLabel == "loop")
         {
            clip.removeEventListener(Event.ENTER_FRAME,onEnterFrame);
            clip.stop();
         }
      }
      
      public function Out() : void
      {
         var clip:MovieClip = m_anmList[m_phase];
         if(!clip)
         {
            return;
         }
         clip.gotoAndPlay("out");
      }
   }
}

